<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">

      
	
	
	<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="FirstSetShow">true</xsl:variable>
<xsl:variable name="SecondSetShow">true</xsl:variable>
<xsl:variable name="GraphType">xl3DColumn</xsl:variable>
<xsl:variable name="ValuesType">abs</xsl:variable>
<xsl:variable name="GraphTitle">SD-4ft Graph</xsl:variable>
<xsl:variable name="LegendShow">false</xsl:variable>
<xsl:variable name="GraphWidth">75e-2</xsl:variable>
<xsl:variable name="GraphHeight">75e-2</xsl:variable>
<xsl:variable name="Chart1Color">#aa20aa</xsl:variable>
<xsl:variable name="Chart2Color">#4040fc</xsl:variable>
<xsl:variable name="AntecedentLabel">antecedent</xsl:variable>
<xsl:variable name="SuccedentLabel">succedent</xsl:variable>
<xsl:variable name="NotAntecedentLabel">¬ antecedent</xsl:variable>
<xsl:variable name="NotSuccedentLabel">¬ succedent</xsl:variable>



	
<msxsl:script language="JScript" implements-prefix="dedek">

	function max4(a, b, c, d)
	{
		return Math.max(a,b,c,d);
	}
	
	function max2(x, y)
	{
		return Math.max(x,y);
	}
	
	function normalize_value(co, cim)
	{
		return Math.round(100*(co/cim));
	}


</msxsl:script>
	
	
	
	

	<xsl:template match="hyp_sd4ft"> <!-- nezpomen prepsat na match="/hyp_4ft" - odebrat lomitko -->


	<!-- hodnoty cisel, souctu a maxima-->
	
	
	<xsl:variable name="sum_set1" select="@a + @b + @c + @d"/>
	<xsl:variable name="sum_r1_set1" select="@a + @b" />
	<xsl:variable name="sum_r2_set1" select="@c + @d" />
	<xsl:variable name="sum_c1_set1" select="@a + @c" />
	<xsl:variable name="sum_c2_set1" select="@b + @d" />
	
	<xsl:variable name="max_set1" select="dedek:max4(number(@a), number(@b), number(@c), number(@d))"/>
	<xsl:variable name="max_r1_set1" select="dedek:max2(number(@a), number(@b))"/>
	<xsl:variable name="max_r2_set1" select="dedek:max2(number(@c), number(@d))"/>
	<xsl:variable name="max_c1_set1" select="dedek:max2(number(@a), number(@c))"/>
	<xsl:variable name="max_c2_set1" select="dedek:max2(number(@b), number(@d))"/>
	
	<xsl:variable name="sum_set2" select="@e + @f + @g + @h"/>
	<xsl:variable name="sum_r1_set2" select="@e + @f" />
	<xsl:variable name="sum_r2_set2" select="@g + @h" />
	<xsl:variable name="sum_c1_set2" select="@e + @g" />
	<xsl:variable name="sum_c2_set2" select="@f + @h" />
	
	<xsl:variable name="max_set2" select="dedek:max4(number(@e), number(@f), number(@g), number(@h))"/>
	<xsl:variable name="max_r1_set2" select="dedek:max2(number(@e), number(@f))"/>
	<xsl:variable name="max_r2_set2" select="dedek:max2(number(@g), number(@h))"/>
	<xsl:variable name="max_c1_set2" select="dedek:max2(number(@e), number(@g))"/>
	<xsl:variable name="max_c2_set2" select="dedek:max2(number(@f), number(@h))"/> 
	
	<!--spocitani hodnot grafu-->
	
	
	
	<!-- First set-->
			
	<xsl:variable name="a">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@a), number($sum_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@a), number($max_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@a), number($sum_c1_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@a), number($sum_r1_set1))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@a" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="b">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@b), number($sum_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@b), number($max_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@b), number($sum_c2_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@b), number($sum_r1_set1))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@b" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="c">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@c), number($sum_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@c), number($max_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@c), number($sum_c1_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@c), number($sum_r2_set1))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@c" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="d">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@d), number($sum_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@d), number($max_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@d), number($sum_c2_set1))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@d), number($sum_r2_set1))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@d" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<!-- Second set-->
	
	<xsl:variable name="e">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@e), number($sum_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@e), number($max_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@e), number($sum_c1_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@e), number($sum_r1_set2))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@e" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="f">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@f), number($sum_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@f), number($max_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@f), number($sum_c2_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@f), number($sum_r1_set2))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@f" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="g">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@g), number($sum_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@g), number($max_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@g), number($sum_c1_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@g), number($sum_r2_set2))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@g" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="h">
		<xsl:choose>
			<xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@h), number($sum_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@h), number($max_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@h), number($sum_c2_set2))" />%</xsl:when>
			<xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@h), number($sum_r2_set2))" />%</xsl:when>
			<xsl:otherwise><xsl:value-of select="@h" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>


	
	<xsl:if test="$FirstSetShow='true' or $SecondSetShow='true'">
		
		<paragraph>
		    	
			<graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{@id}_4ftgraph_1">
				<categories id="categories1_1">
					<xsl:if test="$FirstSetShow='true'">				
						<category title="{$SuccedentLabel}" id="category1_1"></category>
						<category title="{$NotSuccedentLabel}" id="category2_1"></category>
						<xsl:if test="$SecondSetShow='true'">			
							<category title="" id="category_mezera"/>
						</xsl:if>
					</xsl:if>
					<xsl:if test="$SecondSetShow='true'">				
						<category title="{$SuccedentLabel}" id="category1_2"></category>
						<category title="{$NotSuccedentLabel}" id="category2_2"></category>
					</xsl:if>
				</categories>

				<chart title="{$NotAntecedentLabel}" id="chart1_1" color="{$Chart1Color}">
					<xsl:if test="$FirstSetShow='true'">			
						<value value="{$c}" id="value3_1"></value>
						<value value="{$d}" id="value4_1"></value>
						<xsl:if test="$SecondSetShow='true'">			
							<value value="" id="value3_mezera1"></value>
						</xsl:if>
					</xsl:if>
					<xsl:if test="$SecondSetShow='true'">			
						<value value="{$g}" id="value3_2"></value>
						<value value="{$h}" id="value4_2"></value>					
					</xsl:if>
				</chart>
				
				<chart title="{$AntecedentLabel}" id="chart2_1" color="{$Chart2Color}">
					<xsl:if test="$FirstSetShow='true'">			
						<value value="{$a}" id="value1_1"></value>
						<value value="{$b}" id="value2_1"></value>
						<xsl:if test="$SecondSetShow='true'">			
							<value value="" id="value3_mezera2"></value>
						</xsl:if>
					</xsl:if>
					<xsl:if test="$SecondSetShow='true'">			
						<value value="{$e}" id="value1_2"></value>
						<value value="{$f}" id="value2_2"></value>
					</xsl:if>
				</chart>							
				
			</graph>
		  
			
		</paragraph>
		
	</xsl:if>
		
								
	
</xsl:template>
      




</xsl:stylesheet>
