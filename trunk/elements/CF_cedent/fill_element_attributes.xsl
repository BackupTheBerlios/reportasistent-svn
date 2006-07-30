<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
     
     
    <!-- nastaveni jazyka (defaultne cz) -->
	<xsl:variable name="lng">cz</xsl:variable>
 
          
	
	<xsl:template match="CF_cedent">
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				<element_attributes>
				
		
		
				<xsl:apply-templates select="@*"/>
<!--				
				<xsl:text disable-output-escaping="yes">
					&lt;attribute name="categories" value="</xsl:text> 
  				<xsl:apply-templates select="ctgr" /> 
  				<xsl:text disable-output-escaping="yes">"/&gt;</xsl:text>
  
  				<xsl:text disable-output-escaping="yes">
  					&lt;attribute name="missing_values" value="</xsl:text> 
  				<xsl:apply-templates select="missing_value" /> 
  				<xsl:text disable-output-escaping="yes">" /&gt;</xsl:text>
-->

				<xsl:apply-templates select="sub_CF_cedent" mode="recurent_scan" />


				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				</element_attributes>
	</xsl:template>

	
			
	
	
	
	
	
	
	<!-- vypise vsechny atributy -->
	<xsl:template match="@*">
		<xsl:param name="name_prefix" /> 
		<xsl:param name="label_prefix" />
		
		
				<!-- labely polozek-->
		<xsl:variable name="label">
			<xsl:choose>
			
				<!-- nezavisle na jazyce -->
				
				
				<!-- cesky -->
				
				<xsl:when test="$lng='cz'">    
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Databáze</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Datová matice</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Jméno úlohy</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_type'">
								<xsl:text>Typ úlohy</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='cedent_type'">
								<xsl:text>Typ cedentu</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='sub_cedent_cnt'">
								<xsl:text>Počet subcedentů</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='name'">
								<xsl:text>Název</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='literal_cnt'">
								<xsl:text>Počet literálů</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='length'">
								<xsl:text>Délka</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='underlying_attribute'">
								<xsl:text>Podkladový atribut</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='category_cnt'">
								<xsl:text>Počet kategorií</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>
				</xsl:when>
				
				
				<!-- english-->
				
				<xsl:when test="$lng='en'">	
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Database</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Data matrix</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Task name</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_type'">
								<xsl:text>Task type</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='cedent_type'">
								<xsl:text>Cedent type</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='sub_cedent_cnt'">
								<xsl:text>Sub-cedent count</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='name'">
								<xsl:text>Name</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='literal_cnt'">
								<xsl:text>Literal count</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='length'">
								<xsl:text>Length</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='underlying_attribute'">
								<xsl:text>Underlying attribute</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='category_cnt'">
								<xsl:text>Category count</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>	
				</xsl:when>
				
				<!-- jinak se pouzije nazev XML atributu-->
				
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
				
			</xsl:choose>
		</xsl:variable>
			<!-- end of: labely polozek-->
					
					

					<xsl:text disable-output-escaping="yes">
					</xsl:text>
		
		
					<attribute name="{$name_prefix}{name()}" value="{.}" label="{$label_prefix}{$label}" />
	</xsl:template>
	<!-- vypise vsechny atributy -->



			




	<xsl:template match="node()" mode="recurent_scan">
		<xsl:param name="name_prefix" /> 
		<xsl:param name="label_prefix" />



		<!-- labely polozek-->
		<xsl:variable name="label">
			<xsl:choose>
			
				<!-- nezavisle na jazyce -->

				<xsl:when test="name()='sub_CF_cedent'">
					<xsl:text>Subcedent</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='CF_literal'">
					<xsl:text>Literal</xsl:text>
				</xsl:when>
							
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
						
				
			</xsl:choose>
		</xsl:variable>
			<!-- end of: labely polozek-->




		<xsl:apply-templates select="@*">
			<xsl:with-param name="name_prefix">
  				<xsl:value-of select="$name_prefix" />
  				<xsl:value-of select="name()" />
  				<xsl:value-of select="position()" />
  				<xsl:text>_</xsl:text>
  			</xsl:with-param>
  			
  			<xsl:with-param name="label_prefix">
  				<xsl:value-of select="$label_prefix" />
  				<xsl:value-of select="$label" />
  				<xsl:text>(</xsl:text>
  				<xsl:value-of select="position()" />
  				<xsl:text>)</xsl:text>
  				<xsl:text> - </xsl:text>
  			</xsl:with-param>
		</xsl:apply-templates>
		
		<xsl:apply-templates select="*" mode="recurent_scan">
			<xsl:with-param name="name_prefix">
  				<xsl:value-of select="$name_prefix" />
  				<xsl:value-of select="name()" />
  				<xsl:value-of select="position()" />
  				<xsl:text>_</xsl:text>
  			</xsl:with-param>
  			
  			<xsl:with-param name="label_prefix">
  				<xsl:value-of select="$label_prefix" />
  				<xsl:value-of select="$label" />
  				<xsl:text>(</xsl:text>
  				<xsl:value-of select="position()" />
  				<xsl:text>)</xsl:text>
  				<xsl:text> - </xsl:text>
  			</xsl:with-param>
		
		</xsl:apply-templates>
    </xsl:template>
    
</xsl:stylesheet>
