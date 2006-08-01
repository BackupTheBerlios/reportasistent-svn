<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">

  
  
  
   <!-- nastaveni jazyka (defaultne cestina)-->
	<xsl:variable name="lng">cz</xsl:variable>


  
  
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


<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="SumShow">true</xsl:variable>
<xsl:variable name="ShowLegend">true</xsl:variable>
<xsl:variable name="ColourHighlighting">true</xsl:variable>
<xsl:variable name="TypeOfValues">Absolute</xsl:variable>
<xsl:variable name="TablePosition">Horisontal</xsl:variable>
<xsl:variable name="BorderGrey">true</xsl:variable>

      

<!-- nastaveni jazykovych popisku (labelu) -->


<xsl:variable name="label_sum">   <!-- label v tabulce v kolonkach souctu-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">součet</xsl:when>
		<xsl:when test="$lng='en'">sum</xsl:when>
		<xsl:otherwise>sum</xsl:otherwise>
	</xsl:choose>
</xsl:variable>


<xsl:variable name="label_set_number">   <!-- nadpis tabulky: cislo mnoziny-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">Druhá množina</xsl:when>
		<xsl:when test="$lng='en'">Second set</xsl:when>
		<xsl:otherwise>First set</xsl:otherwise>
	</xsl:choose>
</xsl:variable>

<xsl:variable name="label_cat">   <!-- nadpis tabulky: Category-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">Kategorie</xsl:when>
		<xsl:when test="$lng='en'">Category</xsl:when>
		<xsl:otherwise>Category</xsl:otherwise>
	</xsl:choose>
</xsl:variable>

<xsl:variable name="label_freq">   <!-- nadpis tabulky: cislo mnoziny-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">Frekvence</xsl:when>
		<xsl:when test="$lng='en'">Frequency</xsl:when>
		<xsl:otherwise>Frequency</xsl:otherwise>
	</xsl:choose>
</xsl:variable>


    
<!-- TEMPLATES -->


      




	<xsl:template match="hyp_sdcf">
		
		<xsl:variable name="border_color">
			<xsl:choose>
				<xsl:when test="$BorderGrey='true'">#eeeeee</xsl:when>
				<xsl:otherwise>#ffffff</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>


		<xsl:variable name="id_base" select="@id" />
		
		<xsl:variable name="pocet_radku">
			<xsl:choose>
				<xsl:when test="$TablePosition='Horisontal'">
					<xsl:text>2</xsl:text>
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
					<xsl:text>2</xsl:text>
				</xsl:when>
				<xsl:when test="$TablePosition='Horisontal'">
					<xsl:if test="$SumShow='true'"><xsl:value-of select="count(r[position()=1]/c) + 2" /></xsl:if>
					<xsl:if test="$SumShow='false'"><xsl:value-of select="count(r[position()=1]/c) + 1" /></xsl:if>
				</xsl:when>
			</xsl:choose>		
		</xsl:variable>

		
		<xsl:variable name="sum_of_values" select="@sum2" />
		
		<xsl:variable name="total">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="@sum2" />
				</xsl:when>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:text>100</xsl:text>
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		

		<paragraph>
		
			
			<!-- Create element "table"-->
			<xsl:element name="table" >
			    <xsl:attribute name="id"><xsl:value-of select="$id_base"/>table1</xsl:attribute>
			    <xsl:attribute name="cols"><xsl:value-of select="$pocet_sloupcu" /></xsl:attribute>
			    <xsl:attribute name="rows"><xsl:value-of select="$pocet_radku" /></xsl:attribute>
				
				<xsl:variable name="attr_id" select="@attributes" />
				<xsl:variable name="attr_name" select="key('key_ti_attribute',@attributes)/@quant" />
				
				<xsl:for-each select="r[position()=2]">
				
					
					<!-- Horisontal table-->
					
					<xsl:if test="$TablePosition='Horisontal'">
						<tr id="{$id_base}r1">
							<td id="{$id_base}r1d0" bgcolor="{$border_color}">
								<text id="{$id_base}r1d0text"><xsl:value-of select="$label_cat" /> (<xsl:value-of select="$attr_name" />)</text> 
							</td>
							
							<xsl:for-each select="key('key_ti_attribute',$attr_id)/ti_category">
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base" />r1d<xsl:value-of select="position()" />
									</xsl:attribute>
									<text id="{$id_base}r1d{position()}text"><xsl:value-of select="@value" /></text> 
								</xsl:element>
							</xsl:for-each>
							
							<xsl:if test="$SumShow='true'">
								<td id="{$id_base}r1d_sum">
									<text id="{$id_base}r1d_sum_text"><xsl:value-of select="$label_sum" /></text> 
								</td>
							</xsl:if>
						</tr>
						
						<tr id="{$id_base}r2">
							<td id="{$id_base}r2d0" bgcolor="{$border_color}">
								<text id="{$id_base}r1d0text">
									<xsl:value-of select="$label_freq" />
									<xsl:if test="$TypeOfValues='Relative'">
										<xsl:text> (%)</xsl:text>
									</xsl:if>
								</text> 
							</td>
							
							<xsl:for-each select="c">
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base" />r2d<xsl:value-of select="position()" />
									</xsl:attribute>
									<xsl:if test="$ColourHighlighting='true'">
										<xsl:attribute name="bgcolor">
											<xsl:value-of select="dedek:RGB(number(@val), number($sum_of_values))" />
										</xsl:attribute>
									</xsl:if>
									<text id="{$id_base}r1d{position()}text">
										<xsl:choose>
											<xsl:when test="$TypeOfValues='Absolute'">
												<xsl:value-of select="@val" />
											</xsl:when>
											<xsl:when test="$TypeOfValues='Relative'">
												<xsl:value-of select="round((@val div $sum_of_values)*100)" />
											</xsl:when>
										</xsl:choose>
									</text> 
								</xsl:element>
							</xsl:for-each>
							
							<xsl:if test="$SumShow='true'">
								<td id="{$id_base}r2d_sum">
									<text id="{$id_base}r2d_sum_text"><xsl:value-of select="$total" /></text> 
								</td>
							</xsl:if>
						</tr>
					</xsl:if>
					
					
					
					
					<!-- Vertical table-->
					
					<xsl:if test="$TablePosition='Vertical'">
						<tr id="{$id_base}r1">
							<td id="{$id_base}r1d1" bgcolor="{$border_color}">
								<text id="{$id_base}r1d1text"><xsl:value-of select="$label_cat" /> (<xsl:value-of select="$attr_name" />)</text> 
							</td>
							<td id="{$id_base}r1d2" bgcolor="{$border_color}">
								<text id="{$id_base}r1d2text">
									<xsl:value-of select="$label_freq" />
									<xsl:if test="$TypeOfValues='Relative'">
										<xsl:text> (%)</xsl:text>
									</xsl:if>
								</text> 
							</td>							
						</tr>
						
						
						<xsl:for-each select="c">
							<xsl:variable name="pozice" select="position()" />
							<tr id="{$id_base}r{position()}">
								<td id="{$id_base}r{position()}d1">
									<text id="{$id_base}r{position()}d1text">
										<xsl:value-of select="key('key_ti_attribute',$attr_id)/ti_category[position()=$pozice]/@value" />
									</text>
								</td>
								
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base" />r<xsl:value-of select="position()" /><xsl:text>d2</xsl:text>
									</xsl:attribute>
									<xsl:if test="$ColourHighlighting='true'">
										<xsl:attribute name="bgcolor">
											<xsl:value-of select="dedek:RGB(number(@val), number($sum_of_values))" />
										</xsl:attribute>
									</xsl:if>
									<text id="{$id_base}r{position()}d2text">
										<xsl:choose>
											<xsl:when test="$TypeOfValues='Absolute'">
												<xsl:value-of select="@val" />
											</xsl:when>
											<xsl:when test="$TypeOfValues='Relative'">
												<xsl:value-of select="round((@val div $sum_of_values)*100)" />
											</xsl:when>
										</xsl:choose>
									</text> 
								</xsl:element>	
								
							</tr>
						</xsl:for-each>
						
						<xsl:if test="$SumShow='true'">
							<tr id="{$id_base}r_sum">
								<td id="{$id_base}r_sum_d1">
									<text id="{$id_base}r_sum_d1text"><xsl:value-of select="$label_sum" /></text>
								</td>
								
								<td id="{$id_base}r_sum_d2">
									<text id="{$id_base}r_sum_d2text">
										<xsl:value-of select="$total" />
									</text>
								</td>
							</tr>
						</xsl:if>
						
						
					</xsl:if>
				   
				
				
				</xsl:for-each>
							
			</xsl:element>
			
			<!-- Show table legend-->
			<xsl:if test="$ShowLegend='true'">
				<text>
					<br/>
					<xsl:text>Tab:</xsl:text>
					<tab/>
					<xsl:value-of select="$label_set_number" />
					<br/>
				</text>
			</xsl:if>

			
		</paragraph>



	</xsl:template>
	




</xsl:stylesheet>
