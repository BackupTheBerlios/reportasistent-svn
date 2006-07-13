<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">

  <msxsl:script language="JScript" implements-prefix="dedek">

	function RGB(val, max)
	{
		return "#ff"
			 	+ hex2(val/max)
				+ hex2(val/max);
	}

	function hex2(cislo)
	{
		var ret = (255 - Math.round(cislo * 255)).toString(16);

		if (ret.length == 1)
			return "0" + ret;
		else
			return ret;
	}



	function hex(cislo)
	{
		return cislo.toString(16);
	}

  </msxsl:script>


<!-- klic - atributy-->
<xsl:key name="key_ti_attribute" match="ti_attribute" use="@id" />
<!-- klic - hypotezy-->
<xsl:key name="key_hyp_sdcf" match="hyp_sdcf" use="@id" />



<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="SumShow">true</xsl:variable>
<xsl:variable name="ShowLegend">true</xsl:variable>
<xsl:variable name="ColourHighlighting">false</xsl:variable>
<xsl:variable name="TypeOfValues">Absolute</xsl:variable>
<xsl:variable name="TablePosition">Vertical</xsl:variable>
<xsl:variable name="BorderGrey">true</xsl:variable>

      

	<xsl:template match="hyp_sdcf">

		<xsl:variable name="border_color">
			<xsl:choose>
				<xsl:when test="$BorderGrey='true'">#eeeeee</xsl:when>
				<xsl:otherwise>#ffffff</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		
		<xsl:variable name="id_base" select="@id" />
		
		<xsl:variable name="hyp_id" select="@id" />
		
		<xsl:variable name="pocet_radku">
			<xsl:choose>
				<xsl:when test="$TablePosition='Horisontal'">
					<xsl:text>3</xsl:text>
				</xsl:when>
				<xsl:when test="$TablePosition='Vertical'">
					<xsl:if test="$SumShow='true'"><xsl:value-of select="count(r[position()=1]/c) + 2" /></xsl:if>
					<xsl:if test="$SumShow='false'"><xsl:value-of select="count(r[position()=1]/c) + 1" /></xsl:if>
				</xsl:when>
			</xsl:choose>		
		</xsl:variable>
		
		<xsl:variable name="pocet_sloupcu">
			<xsl:choose>
				<xsl:when test="$TablePosition='Vertical'">
					<xsl:text>3</xsl:text>
				</xsl:when>
				<xsl:when test="$TablePosition='Horisontal'">
					<xsl:if test="$SumShow='true'"><xsl:value-of select="count(r[position()=1]/c) + 2" /></xsl:if>
					<xsl:if test="$SumShow='false'"><xsl:value-of select="count(r[position()=1]/c) + 1" /></xsl:if>
				</xsl:when>
			</xsl:choose>		
		</xsl:variable>

		
		<xsl:variable name="sum_of_values_set1" select="@sum1" />
		<xsl:variable name="sum_of_values_set2" select="@sum2" />
		
		<xsl:variable name="total_set1">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="@sum1" />
				</xsl:when>
				<xsl:when test="$TypeOfValues='Relative'">100</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="total_set2">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="@sum2" />
				</xsl:when>
				<xsl:when test="$TypeOfValues='Relative'">100</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		

		
		
		
		
		<paragraph>	
		
			<text id="{$id_base}title_dif">Set differences:</text>
			
			<!-- Create element "table"-->
			<xsl:element name="table" >
			    <xsl:attribute name="id"><xsl:value-of select="$id_base"/>table1</xsl:attribute>
			    <xsl:attribute name="cols"><xsl:value-of select="$pocet_sloupcu" /></xsl:attribute>
			    <xsl:attribute name="rows"><xsl:value-of select="$pocet_radku" /></xsl:attribute>
				
				<xsl:variable name="attr_id" select="@attributes" />
				
				
					
					<!-- Horisontal table-->
					
					<xsl:if test="$TablePosition='Horisontal'">
						<tr id="{$id_base}r1">
							<td id="{$id_base}r1d0" bgcolor="{$border_color}">
								<text id="{$id_base}r1d0text">Category</text> 
							</td>
							
							<xsl:for-each select="key('key_ti_attribute',$attr_id)/ti_category">
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base" />r1d<xsl:value-of select="position()"/>
									</xsl:attribute>
									
									<text id="{$id_base}r1d{position()}text"><xsl:value-of select="@value" /></text> 
								</xsl:element>
							</xsl:for-each>
							
							<xsl:if test="$SumShow='true'">
								<td id="{$id_base}r1d_sum">
									<text id="{$id_base}r1d_sum_text">sum of values</text> 
								</td>
							</xsl:if>
						</tr>
						
						<xsl:for-each select="r">
				
							<xsl:variable name="cislo_radku" select="position()" />
						
					    	<tr id="{$id_base}r{$cislo_radku}">
								<td id="{$id_base}r{$cislo_radku}d0" bgcolor="{$border_color}">
									<text id="{$id_base}r{$cislo_radku}d0text">
										<xsl:if test="$cislo_radku='1'">
											<xsl:text>First set</xsl:text>
										</xsl:if>
										<xsl:if test="$cislo_radku='2'">
											<xsl:text>Second set</xsl:text>
										</xsl:if>
										<xsl:text> frequency</xsl:text>
										<xsl:if test="$TypeOfValues='Relative'">
											<xsl:text> (%)</xsl:text>
										</xsl:if>
									</text> 
								</td>
							
								<xsl:for-each select="c">
									<xsl:element name="td">
										<xsl:attribute name="id">
											<xsl:value-of select="$id_base" />r<xsl:value-of select="$cislo_radku" />d<xsl:value-of select="position()" />
										</xsl:attribute>
										<xsl:if test="$ColourHighlighting='true'">
											<xsl:attribute name="bgcolor">
												<xsl:if test="$cislo_radku='1'">	
													<xsl:value-of select="dedek:RGB(number(@val), number($sum_of_values_set1))" />
												</xsl:if>
												<xsl:if test="$cislo_radku='2'">	
													<xsl:value-of select="dedek:RGB(number(@val), number($sum_of_values_set2))" />
												</xsl:if>
											</xsl:attribute>
										</xsl:if>
										<text id="{$id_base}r{$cislo_radku}d{position()}text">
											<xsl:choose>
												<xsl:when test="$TypeOfValues='Absolute'">
													<xsl:value-of select="@val" />
												</xsl:when>
												<xsl:when test="$TypeOfValues='Relative'">
													<xsl:if test="$cislo_radku='1'">	
														<xsl:value-of select="round((@val div $sum_of_values_set1)*100)" />
													</xsl:if>
													<xsl:if test="$cislo_radku='2'">	
														<xsl:value-of select="round((@val div $sum_of_values_set2)*100)" />
													</xsl:if>	
												</xsl:when>
											</xsl:choose>
										</text> 
									</xsl:element>
								</xsl:for-each>
							
								<xsl:if test="$SumShow='true'">
									<td id="{$id_base}r{$cislo_radku}d_sum">
										<xsl:if test="$cislo_radku='1'">		
											<text id="{$id_base}r2d_sum_text"><xsl:value-of select="$total_set1" /></text> 
										</xsl:if>
										<xsl:if test="$cislo_radku='2'">		
											<text id="{$id_base}r3d_sum_text"><xsl:value-of select="$total_set2" /></text> 
										</xsl:if>
									</td>
								</xsl:if>
							</tr>
							
						</xsl:for-each>	<!-- for-each "r"-->
						
					</xsl:if>
					
						
					
					
					<!-- Vertical table-->
					
					<xsl:if test="$TablePosition='Vertical'">
						<tr id="{$id_base}r1">
							<td id="{$id_base}r1d1" bgcolor="{$border_color}">
								<text id="{$id_base}r1d1text">Category</text> 
							</td>
							<td id="{$id_base}r1d2" bgcolor="{$border_color}">
								<text id="{$id_base}r1d2text">
									<xsl:text>First set frequency</xsl:text>
									<xsl:if test="$TypeOfValues='Relative'">
										<xsl:text> (%)</xsl:text>
									</xsl:if>
								</text> 
							</td>							
							<td id="{$id_base}r1d3" bgcolor="{$border_color}">
								<text id="{$id_base}r1d3text">
									<xsl:text>Second set frequency</xsl:text>
									<xsl:if test="$TypeOfValues='Relative'">
										<xsl:text> (%)</xsl:text>
									</xsl:if>
								</text> 
							</td>		
						</tr>
	
											
						
							<xsl:for-each select="r[position()=1]/c">
								<xsl:variable name="pozice" select="position()" />
								<tr id="{$id_base}r{position()}">
									<td id="{$id_base}r{position()}d1">
										<text id="{$id_base}r{position()}d1text" bgcolor="{$border_color}">
											<xsl:value-of select="key('key_ti_attribute',$attr_id)/ti_category[position()=$pozice]/@value" />
										</text>
									</td>
								
									<xsl:element name="td">
										<xsl:attribute name="id">
											<xsl:value-of select="$id_base" />r<xsl:value-of select="position()" /><xsl:text>d2</xsl:text>
										</xsl:attribute>
										<xsl:if test="$ColourHighlighting='true'">
											<xsl:attribute name="bgcolor">
												<xsl:value-of select="dedek:RGB(number(@val), number($sum_of_values_set1))" />
											</xsl:attribute>
										</xsl:if>
										<text id="{$id_base}r{position()}d2text">
											<xsl:choose>
												<xsl:when test="$TypeOfValues='Absolute'">
													<xsl:value-of select="@val" />
												</xsl:when>
												<xsl:when test="$TypeOfValues='Relative'">
													<xsl:value-of select="round((@val div $sum_of_values_set1)*100)" />
												</xsl:when>
											</xsl:choose>
										</text> 
									</xsl:element>
									
									<xsl:element name="td">
										<xsl:attribute name="id">
											<xsl:value-of select="$id_base" />r<xsl:value-of select="position()" /><xsl:text>d3</xsl:text>
										</xsl:attribute>
										
										<xsl:variable name="val" select="key('key_hyp_sdcf',$hyp_id)/r[position()=2]/c[position()=$pozice]/@val" />
										
										<xsl:if test="$ColourHighlighting='true'">
											<xsl:attribute name="bgcolor">
												<xsl:value-of select="dedek:RGB(number($val), number($sum_of_values_set2))" />
											</xsl:attribute>
										</xsl:if>
										<text id="{$id_base}r{position()}d3text">
											<xsl:choose>
												<xsl:when test="$TypeOfValues='Absolute'">
													<xsl:value-of select="$val" />
												</xsl:when>
												<xsl:when test="$TypeOfValues='Relative'">
													<xsl:value-of select="round(($val div $sum_of_values_set2)*100)" />
												</xsl:when>
											</xsl:choose>
										</text> 
									</xsl:element>	
									
									
								</tr>
							</xsl:for-each>
						
							<xsl:if test="$SumShow='true'">
								<tr id="{$id_base}r_sum">
									<td id="{$id_base}r_sum_d1">
										<text id="{$id_base}r_sum_d1text">sum of values</text>
									</td>
									
									<td id="{$id_base}r_sum_d2">
										<text id="{$id_base}r_sum_d2text">
											<xsl:value-of select="$total_set1" />
										</text>
									</td>
									
									<td id="{$id_base}r_sum_d3">
										<text id="{$id_base}r_sum_d3text">
											<xsl:value-of select="$total_set2" />
										</text>
									</td>
								</tr>
							</xsl:if>
						
						
						
					</xsl:if>
				   
				
				
				
							
			</xsl:element>
			
			<!-- Show table legend-->
			<xsl:if test="$ShowLegend='true'">
				<text id="{$id_base}tab_dif_legend">
					<br/>
					<xsl:text>Attribute name: </xsl:text>
					<tab/>
					<xsl:value-of select="key('key_ti_attribute',@attributes)/@quant" />
					<br/>
				</text>
			</xsl:if>
		
		</paragraph>


		



	</xsl:template>
	




</xsl:stylesheet>
